/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dto;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author homya
 */
@Entity
@Table(name = "MECHANIK")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Mechanik.findAll", query = "SELECT m FROM Mechanik m")
    , @NamedQuery(name = "Mechanik.findByIdM", query = "SELECT m FROM Mechanik m WHERE m.idM = :idM")
    , @NamedQuery(name = "Mechanik.findByJmenoM", query = "SELECT m FROM Mechanik m WHERE m.jmenoM = :jmenoM")
    , @NamedQuery(name = "Mechanik.findBySpecializaceM", query = "SELECT m FROM Mechanik m WHERE m.specializaceM = :specializaceM")})
public class Mechanik implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_M")
    private Integer idM;
    @Size(max = 255)
    @Column(name = "JMENO_M")
    private String jmenoM;
    @Size(max = 255)
    @Column(name = "SPECIALIZACE_M")
    private String specializaceM;
    @OneToMany(mappedBy = "idM", fetch = FetchType.EAGER)
    private List<Oprava> opravaList;

    public Mechanik() {
    }

    public Mechanik(Integer idM) {
        this.idM = idM;
    }

    public Integer getIdM() {
        return idM;
    }

    public void setIdM(Integer idM) {
        this.idM = idM;
    }

    public String getJmenoM() {
        return jmenoM;
    }

    public void setJmenoM(String jmenoM) {
        this.jmenoM = jmenoM;
    }

    public String getSpecializaceM() {
        return specializaceM;
    }

    public void setSpecializaceM(String specializaceM) {
        this.specializaceM = specializaceM;
    }

    @XmlTransient
    public List<Oprava> getOpravaList() {
        return opravaList;
    }

    public void setOpravaList(List<Oprava> opravaList) {
        this.opravaList = opravaList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idM != null ? idM.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Mechanik)) {
            return false;
        }
        Mechanik other = (Mechanik) object;
        if ((this.idM == null && other.idM != null) || (this.idM != null && !this.idM.equals(other.idM))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "db.Mechanik[ idM=" + idM + " ]";
    }
    
}
