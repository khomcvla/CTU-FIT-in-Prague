/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package service;

import db.Auto;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author homya
 */
@Stateless
public class AutoFacade extends AbstractFacade<Auto> implements AutoFacadeLocal {

    @PersistenceContext(unitName = "SemPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public AutoFacade() {
        super(Auto.class);
    }
    
}
