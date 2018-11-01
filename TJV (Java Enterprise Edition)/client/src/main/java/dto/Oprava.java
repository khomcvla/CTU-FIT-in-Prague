/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dto;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author homya
 */
@Entity
@Table(name = "OPRAVA")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Oprava.findAll", query = "SELECT o FROM Oprava o")
    , @NamedQuery(name = "Oprava.findByIdO", query = "SELECT o FROM Oprava o WHERE o.idO = :idO")
    , @NamedQuery(name = "Oprava.findByCenaO", query = "SELECT o FROM Oprava o WHERE o.cenaO = :cenaO")
    , @NamedQuery(name = "Oprava.findByDiagnostikaO", query = "SELECT o FROM Oprava o WHERE o.diagnostikaO = :diagnostikaO")})
public class Oprava implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_O")
    private Integer idO;
    @Column(name = "CENA_O")
    private Integer cenaO;
    @Size(max = 255)
    @Column(name = "DIAGNOSTIKA_O")
    private String diagnostikaO;
    @JoinColumn(name = "ID_A", referencedColumnName = "ID_A")
    @ManyToOne(fetch = FetchType.EAGER)
    private Auto idA;
    @JoinColumn(name = "ID_M", referencedColumnName = "ID_M")
    @ManyToOne(fetch = FetchType.EAGER)
    private Mechanik idM;

    public Oprava() {
    }

    public Oprava(Integer idO) {
        this.idO = idO;
    }

    public Integer getIdO() {
        return idO;
    }

    public void setIdO(Integer idO) {
        this.idO = idO;
    }

    public Integer getCenaO() {
        return cenaO;
    }

    public void setCenaO(Integer cenaO) {
        this.cenaO = cenaO;
    }

    public String getDiagnostikaO() {
        return diagnostikaO;
    }

    public void setDiagnostikaO(String diagnostikaO) {
        this.diagnostikaO = diagnostikaO;
    }

    public Auto getIdA() {
        return idA;
    }

    public void setIdA(Auto idA) {
        this.idA = idA;
    }

    public Mechanik getIdM() {
        return idM;
    }

    public void setIdM(Mechanik idM) {
        this.idM = idM;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idO != null ? idO.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Oprava)) {
            return false;
        }
        Oprava other = (Oprava) object;
        if ((this.idO == null && other.idO != null) || (this.idO != null && !this.idO.equals(other.idO))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "db.Oprava[ idO=" + idO + " ]";
    }
    
}
