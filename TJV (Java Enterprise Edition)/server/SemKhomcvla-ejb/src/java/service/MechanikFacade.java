/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package service;

import db.Mechanik;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author homya
 */
@Stateless
public class MechanikFacade extends AbstractFacade<Mechanik> implements MechanikFacadeLocal {

    @PersistenceContext(unitName = "SemPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public MechanikFacade() {
        super(Mechanik.class);
    }
    
}
